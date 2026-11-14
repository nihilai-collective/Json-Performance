
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1037.58 | 0.174065 | 8068.69ms | 2251027 | 160 | 2.07521e+09 | 2.06899e+06 | 0.101163 | 1(Win) | true |
| Jsonifier (two-stage) | 896.457 | 0.194363 | 9069.83ms | 2251027 | 160 | 3.46617e+09 | 2.3947e+06 | 0.266799 | 2(Loss) | true |
| Glaze | 692.889 | 0.753594 | 5469.9ms | 2251027 | 30 | 1.63543e+10 | 3.09826e+06 | 0.0148384 | 3(Loss) | true |
| simdjson (ondemand) | 617.641 | 0.177984 | 6048.92ms | 2251027 | 30 | 1.14808e+09 | 3.47572e+06 | 0.105723 | 4(Loss) | true |
