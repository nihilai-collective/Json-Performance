
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13203.8 | 0.0217147 | 4065.68ms | 461466 | 4890 | 256151 | 33330.4 | 0.00639016 | 0.386726 | 2.09417 | 0.103752 | 1.0944e-05 | 3.3901e-06 | 2.8858e-06 | 1(Win) | true |
| simdjson (stage-1) | 11659 | 0.0272802 | 4518.13ms | 461466 | 1280 | 135724 | 37746.5 | 0.137337 | 0.440247 | 2.14083 | 0.092022 | 1.71938e-05 | 2.10775e-06 | 1.67774e-06 | 2(Loss) | true |
