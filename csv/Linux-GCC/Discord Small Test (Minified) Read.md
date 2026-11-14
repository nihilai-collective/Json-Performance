
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1501.1 | 0.132418 | 1027.17ms | 4857 | 320 | 5342.75 | 3085.74 | 0.0836821 | 3.48164 | 14.1666 | 2.73296 | 0.000938079 | 8.62158e-05 | 3.41003e-05 | 1(Win) | true |
| simdjson (ondemand) | 1421.33 | 0.0557244 | 1045.24ms | 4857 | 1280 | 4221.32 | 3258.92 | 0.0668152 | 3.6679 | 14.2837 | 2.54293 | 0.00135581 | 2.7988e-05 | 2.57361e-06 | 2(Loss) | true |
