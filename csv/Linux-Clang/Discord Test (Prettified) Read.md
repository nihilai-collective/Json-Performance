
----
### Discord Test (Prettified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13408.4 | 0.0346782 | 1317.62ms | 83958 | 1280 | 5489 | 5971.53 | 0.0515332 | 0.386506 | 2.08926 | 0.0970248 | 3.76956e-05 | 1.32135e-06 | 2.79157e-08 | 1(Win) | true |
| simdjson (stage-1) | 12663.8 | 0.0183583 | 1351.25ms | 83958 | 160 | 215.566 | 6322.64 | 0.0590781 | 0.409367 | 1.97265 | 0.0848162 | 4.60051e-05 | 1.48884e-06 | 7.4442e-08 | 2(Loss) | true |
