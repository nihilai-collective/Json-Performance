
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) DID NOT CONVERGE | 1463.12 | 1.34522 | 6764.17ms | 5373214 | 30 | 6.65915e+10 | 3.50231e+06 | 5.33996 | -(Win) | false |
| Jsonifier (two-stage) | 1339.11 | 1.14998 | 6815.02ms | 5373214 | 30 | 5.80948e+10 | 3.82664e+06 | 0.345564 | 2(Loss) | true |
| Jsonifier | 1268.23 | 0.915098 | 6703.11ms | 5373214 | 80 | 1.0937e+11 | 4.04051e+06 | 1.22351 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 1176.48 | 0.86162 | 7802.11ms | 5373214 | 80 | 1.12674e+11 | 4.35563e+06 | 1.51796 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1149.39 | 1.61165 | 7293.62ms | 5373214 | 40 | 2.06509e+11 | 4.45828e+06 | 0.95383 | 4(Tie) | true |
