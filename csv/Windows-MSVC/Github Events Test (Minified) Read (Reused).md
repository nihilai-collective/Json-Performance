
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1568.07 | 0.0880028 | 4094.94ms | 53331 | 40 | 32589.7 | 32435 | 0.00513875 | 1.57746 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1366.94 | 0.410968 | 4542.58ms | 53331 | 160 | 3.74108e+06 | 37207.5 | 0.358183 | 1.81003 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1364.32 | 0.22003 | 4533.47ms | 53331 | 640 | 4.30601e+06 | 37279.1 | 0.226657 | 1.81321 | 2(Tie) | true |
| simdjson (ondemand) | 828.463 | 0.675116 | 6890.65ms | 53331 | 80 | 1.37423e+07 | 61391.2 | 0.0468527 | 2.98708 | 4(Loss) | true |
