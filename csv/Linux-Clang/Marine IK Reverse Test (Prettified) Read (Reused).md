
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2740.68 | 0.336736 | 8776.27ms | 7351818 | 40 | 2.96834e+09 | 2.55822e+06 | 0.578813 | 0.90331 | 1(Win) | true |
| Jsonifier | 2602.88 | 0.489744 | 9276.03ms | 7351818 | 160 | 2.78445e+10 | 2.69365e+06 | 0.174992 | 0.951161 | 2(Loss) | true |
| simdjson (ondemand) | 2179.78 | 1.44608 | 5180.96ms | 7351818 | 80 | 1.73075e+11 | 3.21648e+06 | 2.02446 | 1.13573 | 3(Loss) | true |
| Glaze | 2037.72 | 0.193717 | 5651.06ms | 7351818 | 40 | 1.77705e+09 | 3.44074e+06 | 0.709996 | 1.21488 | 4(Loss) | true |
