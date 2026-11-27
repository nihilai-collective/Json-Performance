
----
### Marine IK Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 4366.51 | 0.0651247 | 5214.02ms | 1834197 | 640 | 4.35607e+07 | 400601 | 0.135838 | 1.17547 | 6.3732 | 0.867841 | 0.00352372 | 0.0752987 | 0.000178528 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 4327.16 | 0.515147 | 5254.65ms | 1834197 | 320 | 1.38771e+09 | 404243 | 0.135351 | 1.18826 | 6.02484 | 0.923116 | 0.00634406 | 0.0755499 | 5.88575e-05 | 1(Tie) | true |
