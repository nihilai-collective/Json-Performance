
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 646.734 | 0.414446 | 683.805ms | 4630 | 2560 | 2.04968e+06 | 6827.4 | 0.719913 | 1(Win) | true |
| Jsonifier (two-stage) | 571.129 | 0.551842 | 807.447ms | 4630 | 320 | 582469 | 7731.2 | 0.897891 | 2(Loss) | true |
| simdjson (reflection) | 509.663 | 0.34889 | 874.423ms | 4630 | 2560 | 2.33892e+06 | 8663.6 | 0.428906 | 3(Loss) | true |
| Glaze | 482.253 | 0.584279 | 939.192ms | 4630 | 640 | 1.83161e+06 | 9156 | 1.20846 | 4(Loss) | true |
| simdjson (ondemand) | 456.761 | 0.115819 | 1014.43ms | 4630 | 4890 | 612993 | 9667.01 | 2.40469 | 5(Loss) | true |
