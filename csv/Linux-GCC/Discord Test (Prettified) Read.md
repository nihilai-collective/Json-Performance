
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13541.2 | 0.0304672 | 1317.02ms | 83958 | 4890 | 15870.2 | 5912.95 | 0.0896114 | 0.383574 | 2.04176 | 0.117452 | 2.44133e-05 | 3.10312e-06 | 5.94318e-07 | 1(Win) | true |
| simdjson (stage-1) | 12973.2 | 0.0720064 | 1336.85ms | 83958 | 2560 | 50560.9 | 6171.87 | 0.0431839 | 0.400264 | 2.18387 | 0.084447 | 4.04964e-05 | 3.52669e-06 | 8.09557e-07 | 2(Loss) | true |
