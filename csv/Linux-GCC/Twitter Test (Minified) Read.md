
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15343.7 | 0.133104 | 3652.2ms | 466906 | 30 | 44761.3 | 29020.1 | 0.0231969 | 0.335913 | 1.68483 | 0.0697443 | 2.70576e-05 | 6.63231e-05 | 6.44669e-05 | 1(Win) | true |
| simdjson (stage-1) | 13936.3 | 0.0308916 | 3922.82ms | 466906 | 4890 | 476376 | 31950.7 | 0.0529718 | 0.368248 | 1.92737 | 0.0728648 | 2.42426e-05 | 1.9635e-06 | 1.15366e-06 | 2(Loss) | true |
