// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2022 MediaTek Inc.
 * Author: Chong-ming Wei <chong-ming.wei@mediatek.com>
 */

#include <linux/clk-provider.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>

#include "clk-mtk.h"
#include "clk-gate.h"

#include <dt-bindings/clock/mt6886-clk.h>

#define MT_CCF_BRINGUP		1

/* Regular Number Definition */
#define INV_OFS			-1
#define INV_BIT			-1

static const struct mtk_gate_regs mdp_cg_regs = {
	.set_ofs = 0x104,
	.clr_ofs = 0x108,
	.sta_ofs = 0x100,
};

#define GATE_MDP(_id, _name, _parent, _shift) {	\
		.id = _id,				\
		.name = _name,				\
		.parent_name = _parent,			\
		.regs = &mdp_cg_regs,			\
		.shift = _shift,			\
		.ops = &mtk_clk_gate_ops_setclr,	\
	}

static const struct mtk_gate mdp_clks[] = {
	GATE_MDP(CLK_MDP_MUTEX0, "mdp_mutex0",
			"mdp0_ck"/* parent */, 0),
	GATE_MDP(CLK_MDP_APB_BUS, "mdp_apb_bus",
			"mdp0_ck"/* parent */, 1),
	GATE_MDP(CLK_MDP_SMI0, "mdp_smi0",
			"mdp0_ck"/* parent */, 2),
	GATE_MDP(CLK_MDP_RDMA0, "mdp_rdma0",
			"mdp0_ck"/* parent */, 3),
	GATE_MDP(CLK_MDP_HDR0, "mdp_hdr0",
			"mdp0_ck"/* parent */, 5),
	GATE_MDP(CLK_MDP_AAL0, "mdp_aal0",
			"mdp0_ck"/* parent */, 6),
	GATE_MDP(CLK_MDP_RSZ0, "mdp_rsz0",
			"mdp0_ck"/* parent */, 7),
	GATE_MDP(CLK_MDP_TDSHP0, "mdp_tdshp0",
			"mdp0_ck"/* parent */, 8),
	GATE_MDP(CLK_MDP_COLOR0, "mdp_color0",
			"mdp0_ck"/* parent */, 9),
	GATE_MDP(CLK_MDP_WROT0, "mdp_wrot0",
			"mdp0_ck"/* parent */, 10),
	GATE_MDP(CLK_MDP_FAKE_ENG0, "mdp_fake_eng0",
			"mdp0_ck"/* parent */, 11),
	GATE_MDP(CLK_MDP_DL_RELAY0, "mdp_dl_relay0",
			"mdp0_ck"/* parent */, 12),
	GATE_MDP(CLK_MDP_DL_RELAY1, "mdp_dl_relay1",
			"mdp0_ck"/* parent */, 13),
	GATE_MDP(CLK_MDP_RDMA1, "mdp_rdma1",
			"mdp0_ck"/* parent */, 15),
	GATE_MDP(CLK_MDP_HDR1, "mdp_hdr1",
			"mdp0_ck"/* parent */, 17),
	GATE_MDP(CLK_MDP_AAL1, "mdp_aal1",
			"mdp0_ck"/* parent */, 18),
	GATE_MDP(CLK_MDP_RSZ1, "mdp_rsz1",
			"mdp0_ck"/* parent */, 19),
	GATE_MDP(CLK_MDP_TDSHP1, "mdp_tdshp1",
			"mdp0_ck"/* parent */, 20),
	GATE_MDP(CLK_MDP_COLOR1, "mdp_color1",
			"mdp0_ck"/* parent */, 21),
	GATE_MDP(CLK_MDP_WROT1, "mdp_wrot1",
			"mdp0_ck"/* parent */, 22),
	GATE_MDP(CLK_MDP_DLO_ASYNC0, "mdp_dlo_async0",
			"mdp0_ck"/* parent */, 26),
	GATE_MDP(CLK_MDP_DLO_ASYNC1, "mdp_dlo_async1",
			"mdp0_ck"/* parent */, 30),
	GATE_MDP(CLK_MDP_HRE_TOP_MDPSYS, "mdp_hre_mdpsys",
			"mdp0_ck"/* parent */, 31),
};

static const struct mtk_clk_desc mdp_mcd = {
	.clks = mdp_clks,
	.num_clks = CLK_MDP_NR_CLK,
};

static const struct of_device_id of_match_clk_mt6886_mdpsys[] = {
	{
		.compatible = "mediatek,mt6886-mdpsys",
		.data = &mdp_mcd,
	}, {
		/* sentinel */
	}
};


static int clk_mt6886_mdpsys_grp_probe(struct platform_device *pdev)
{
	int r;

#if MT_CCF_BRINGUP
	pr_notice("%s: %s init begin\n", __func__, pdev->name);
#endif

	r = mtk_clk_simple_probe(pdev);
	if (r)
		dev_err(&pdev->dev,
			"could not register clock provider: %s: %d\n",
			pdev->name, r);

#if MT_CCF_BRINGUP
	pr_notice("%s: %s init end\n", __func__, pdev->name);
#endif

	return r;
}

static struct platform_driver clk_mt6886_mdpsys_drv = {
	.probe = clk_mt6886_mdpsys_grp_probe,
	.driver = {
		.name = "clk-mt6886-mdpsys",
		.of_match_table = of_match_clk_mt6886_mdpsys,
	},
};

module_platform_driver(clk_mt6886_mdpsys_drv);
MODULE_LICENSE("GPL");
