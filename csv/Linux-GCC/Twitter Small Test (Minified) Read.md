
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2179.05 | 0.062755 | 842.888ms | 2821 | 4890 | 2935.46 | 1234.63 | 0.0904389 | 2.42071 | 9.1067 | 1.62921 | 0.000361371 | 7.45214e-05 | 1.92103e-05 | 1(Win) | true |
| simdjson (ondemand) | 2054.53 | 0.0661543 | 849.016ms | 2821 | 320 | 240.129 | 1309.45 | 0.0021478 | 2.5849 | 9.486 | 1.55335 | 0.000367777 | 5.20649e-05 | 4.43105e-06 | 2(Loss) | true |
