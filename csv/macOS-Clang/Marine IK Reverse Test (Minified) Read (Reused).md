
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 722.15 | 1.13164 | 8567.78ms | 1834197 | 40 | 3.00549e+10 | 2.42225e+06 | 2.2579 | 1(Win) | true |
| Jsonifier (two-stage) | 636.871 | 0.207674 | 9769.45ms | 1834197 | 80 | 2.60281e+09 | 2.74659e+06 | 0.132479 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 429.379 | 0.648315 | 6738.97ms | 1834197 | 80 | 5.5805e+10 | 4.07385e+06 | 0.625912 | 3(Tie) | true |
| Glaze STATISTICAL TIE DID NOT CONVERGE | 421.148 | 0.981524 | 6524.22ms | 1834197 | 80 | 1.32958e+11 | 4.15347e+06 | 8.71504 | -(Tie) | false |
