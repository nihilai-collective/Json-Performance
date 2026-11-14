
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 803.455 | 0.853416 | 6065.06ms | 7351818 | 30 | 1.66383e+11 | 8.72637e+06 | 0.517927 | 3.08136 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 784.158 | 1.44444 | 6268.57ms | 7351818 | 40 | 6.67176e+11 | 8.9411e+06 | 1.19085 | 3.15723 | 1(Tie) | true |
