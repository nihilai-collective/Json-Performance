
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 362.48 | 0.484474 | 7244.93ms | 1834197 | 80 | 4.37274e+10 | 4.82572e+06 | 0.368031 | 8.38464 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 358.302 | 0.624405 | 7428.34ms | 1834197 | 80 | 7.43392e+10 | 4.882e+06 | 0.423689 | 8.48242 | 1(Tie) | true |
