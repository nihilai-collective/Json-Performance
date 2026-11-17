
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 361.399 | 0.42337 | 7387.53ms | 1834197 | 80 | 3.3593e+10 | 4.84015e+06 | 0.466748 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 358.438 | 0.386275 | 7119.65ms | 1834197 | 80 | 2.8428e+10 | 4.88014e+06 | 0.105226 | 1(Tie) | true |
