
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1849.33 | 0.114515 | 8428.54ms | 5212421 | 80 | 7.57989e+08 | 2.68798e+06 | 0.823541 | 2.76212 | 13.0195 | 2.55373 | 0.0100345 | 0.0604931 | 0.000891723 | 1(Win) | true |
| simdjson (ondemand) | 1803.05 | 0.693221 | 8521.34ms | 5212421 | 80 | 2.92211e+10 | 2.75697e+06 | 0.0142745 | 2.80702 | 13.0109 | 2.29201 | 0.0102526 | 0.0606016 | 0.000332453 | 2(Loss) | true |
