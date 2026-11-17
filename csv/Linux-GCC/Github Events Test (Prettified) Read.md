
----
### Github Events Test (Prettified) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15958.2 | 0.0220195 | 1109.53ms | 65103 | 4890 | 3588.87 | 3890.61 | 0.0441839 | 0.32555 | 1.60621 | 0.0591377 | 3.11415e-05 | 2.47209e-06 | 3.98927e-07 | 1(Win) | true |
| simdjson (stage-1) | 15852.3 | 0.0485161 | 1106.85ms | 65103 | 80 | 288.853 | 3916.59 | 0.00670271 | 0.328402 | 1.67697 | 0.0621477 | 3.01445e-05 | 2.68805e-06 | 0 | 2(Loss) | true |
