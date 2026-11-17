
----
### Marine IK Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8941.92 | 0.551833 | 290.319ms | 24579 | 1280 | 267850 | 2621.4 | 0.0228938 | 1(Win) | true |
| Glaze | 3259.21 | 0.104043 | 725.343ms | 24579 | 4890 | 273805 | 7192.03 | 0.0184884 | 2(Loss) | true |
| simdjson (reflection) | 322.443 | 0.211131 | 7706.9ms | 24893 | 320 | 7.73222e+06 | 73624.8 | 0.0597268 | 3(Loss) | true |
