
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11485 | 0.076411 | 1185.06ms | 56369 | 1280 | 16373.6 | 4680.7 | 0.0155249 | 0.452399 | 2.32839 | 0.115844 | 8.50146e-05 | 3.09068e-06 | 1.03947e-06 | 1(Win) | true |
| simdjson (stage-1) | 10431.4 | 0.0210767 | 1229.77ms | 56369 | 4890 | 5769.09 | 5153.42 | 0.00579385 | 0.497312 | 2.37178 | 0.103621 | 3.48601e-05 | 2.04249e-06 | 6.16737e-08 | 2(Loss) | true |
