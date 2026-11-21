
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 589.068 | 2.32754 | 8840.06ms | 1834197 | 30 | 1.4331e+11 | 2.96948e+06 | 1.9658 | 1(Win) | true |
| Jsonifier (two-stage) DID NOT CONVERGE | 554.997 | 0.246161 | 10229.9ms | 1834197 | 160 | 9.63096e+09 | 3.15178e+06 | 7.53197 | -(Loss) | false |
| simdjson (ondemand) STATISTICAL TIE | 410.14 | 0.0985526 | 6530.59ms | 1834197 | 30 | 5.30012e+08 | 4.26495e+06 | 0.398018 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 408.154 | 0.779001 | 6609.8ms | 1834197 | 30 | 3.34381e+10 | 4.28571e+06 | 2.7944 | 3(Tie) | true |
