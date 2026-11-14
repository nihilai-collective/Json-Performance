
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1029.75 | 0.16766 | 755.345ms | 8150 | 1280 | 204984 | 7547.89 | 0.0984272 | 2.94264 | 1(Win) | true |
| simdjson (ondemand) | 947.882 | 0.26795 | 823.343ms | 8150 | 2560 | 1.23582e+06 | 8199.8 | 0.255165 | 3.19849 | 2(Loss) | true |
