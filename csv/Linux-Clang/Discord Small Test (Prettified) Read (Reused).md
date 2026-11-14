
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2845.75 | 0.116539 | 991.131ms | 6701 | 4890 | 33492.1 | 2245.66 | 0.10024 | 1.80914 | 7.47023 | 1.17505 | 0.000893314 | 4.14125e-05 | 1.17798e-05 | 1(Win) | true |
| Glaze | 2634.38 | 0.102246 | 1004.88ms | 6701 | 4890 | 30083.5 | 2425.84 | 0.117806 | 1.95207 | 8.86704 | 1.67975 | 0.00112 | 4.13515e-05 | 1.17493e-05 | 2(Loss) | true |
| Jsonifier | 1966.04 | 0.141221 | 1092.97ms | 6701 | 4890 | 103039 | 3250.48 | 0.140383 | 2.60477 | 8.42337 | 1.73556 | 0.00154035 | 4.05885e-05 | 1.35804e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1171.21 | 0.122426 | 1310.91ms | 6701 | 1280 | 57116.9 | 5456.36 | 0.0315672 | 4.34466 | 15.3855 | 2.54216 | 0.00264571 | 7.77636e-05 | 3.03126e-05 | 4(Loss) | true |
