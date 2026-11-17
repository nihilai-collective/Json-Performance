
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 360.765 | 1.08619 | 7257.71ms | 1834197 | 30 | 8.32099e+10 | 4.84867e+06 | 1.29212 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 350.143 | 1.09228 | 7469.69ms | 1834197 | 40 | 1.19105e+11 | 4.99575e+06 | 1.18331 | 1(Tie) | true |
