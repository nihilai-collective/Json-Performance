
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13192.4 | 0.0466546 | 4056.6ms | 461466 | 640 | 155024 | 33359.2 | 0.0279705 | 0.387229 | 2.09417 | 0.103752 | 3.05887e-05 | 1.52029e-06 | 1.11736e-06 | 1(Win) | true |
| simdjson (stage-1) | 11635.3 | 0.0306163 | 4510.68ms | 461466 | 4890 | 655751 | 37823.5 | 0.0940896 | 0.440192 | 2.14083 | 0.092022 | 7.6829e-06 | 5.61162e-06 | 4.94113e-06 | 2(Loss) | true |
