
----
### Marine IK Reverse Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1885.52 | 0.13646 | 961.337ms | 18245 | 2560 | 405951 | 9228.1 | 0.192174 | 1(Win) | true |
| simdjson (reflection) | 1803.46 | 0.159973 | 974.858ms | 18245 | 2560 | 609825 | 9648 | 0.0726066 | 2(Loss) | true |
| Jsonifier | 1747 | 0.114751 | 998.996ms | 18245 | 4890 | 638743 | 9959.81 | 0.551362 | 3(Loss) | true |
| simdjson (ondemand) | 1367.26 | 0.273498 | 1279ms | 18245 | 640 | 775307 | 12726 | 0.255247 | 4(Loss) | true |
| Glaze | 1337.29 | 0.139016 | 1336.49ms | 18245 | 80 | 26172.9 | 13011.2 | 0.0982801 | 5(Loss) | true |
