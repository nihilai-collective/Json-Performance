
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2242.27 | 0.111536 | 188.867ms | 4390 | 80 | 346.956 | 1867.14 | 0.197106 | 1.08862 | 1(Win) | true |
| Jsonifier (two-stage) | 1849.44 | 0.0983896 | 231.055ms | 4390 | 30 | 148.823 | 2263.73 | 0.0735705 | 1.32229 | 2(Loss) | true |
| Glaze | 1743.69 | 0.082262 | 244.056ms | 4390 | 80 | 312.088 | 2401.01 | 0.110768 | 1.40473 | 3(Loss) | true |
| simdjson (ondemand) | 1066.08 | 0.136098 | 395.362ms | 4390 | 4890 | 139689 | 3927.14 | 0.0492935 | 2.30688 | 4(Loss) | true |
