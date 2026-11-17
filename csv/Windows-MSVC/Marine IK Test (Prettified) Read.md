
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1316.48 | 0.913324 | 7972.31ms | 7351818 | 30 | 7.09789e+10 | 5.32573e+06 | 0.145995 | 2.30858 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1314.37 | 0.906106 | 8095.82ms | 7351818 | 40 | 9.34488e+10 | 5.3343e+06 | 0.844543 | 2.31228 | 1(Tie) | true |
