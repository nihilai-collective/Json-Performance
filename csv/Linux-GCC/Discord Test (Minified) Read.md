
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11378.4 | 0.0476012 | 1191.74ms | 56369 | 160 | 809.242 | 4724.56 | 0.112186 | 0.456713 | 2.30423 | 0.154092 | 0.000155782 | 3.3263e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 10744.3 | 0.044425 | 1220.89ms | 56369 | 40 | 197.625 | 5003.38 | 0.0224798 | 0.483392 | 2.59153 | 0.103035 | 3.45935e-05 | 3.54805e-06 | 1.33052e-06 | 2(Loss) | true |
