
----
### Random Test (Minified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12505.9 | 0.0433368 | 4248.2ms | 461466 | 2560 | 595392 | 35190.4 | 0.0288059 | 0.40952 | 2.04594 | 0.0861841 | 7.93328e-06 | 4.33655e-06 | 2.93308e-06 | 1(Win) | true |
| simdjson (stage-1) | 11667.9 | 0.0324081 | 4514.94ms | 461466 | 4890 | 730652 | 37717.9 | 0.166562 | 0.438667 | 2.34282 | 0.0920242 | 1.43138e-05 | 3.73089e-06 | 2.28356e-06 | 2(Loss) | true |
