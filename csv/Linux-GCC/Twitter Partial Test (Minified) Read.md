
----
### Twitter Partial Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 7984.77 | 0.0548605 | 6332.23ms | 466906 | 1280 | 1.19802e+06 | 55765.7 | 0.171913 | 0.634248 | 3.08981 | 0.371932 | 0.000857891 | 1.27552e-05 | 9.77177e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 7944.25 | 0.0369511 | 6345.4ms | 466906 | 2560 | 1.09811e+06 | 56050.1 | 0.107691 | 0.634373 | 3.08868 | 0.371668 | 0.00085657 | 3.00348e-06 | 1.76193e-06 | 2(Loss) | true |
| simdjson (reflection) | 6967.23 | 0.0192337 | 7132.7ms | 466906 | 4890 | 738880 | 63910.1 | 0.0225276 | 0.725478 | 3.56443 | 0.370401 | 0.000853698 | 9.34621e-06 | 7.49309e-06 | 3(Loss) | true |
| simdjson (ondemand) | 6791.46 | 0.0183769 | 7302.38ms | 466906 | 2560 | 371634 | 65564.1 | 0.0310551 | 0.74403 | 3.59603 | 0.371035 | 0.000753019 | 5.18289e-06 | 3.24192e-06 | 4(Loss) | true |
| Glaze | 3229 | 0.0432974 | 7425.45ms | 466906 | 2560 | 9.12612e+06 | 137899 | 0.0466213 | 1.56454 | 6.44431 | 1.02742 | 0.00150494 | 1.14576e-05 | 7.32548e-06 | 5(Loss) | true |
