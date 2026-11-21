
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 891.883 | 0.0890881 | 9413.71ms | 2251027 | 40 | 1.83927e+08 | 2.40698e+06 | 0.126927 | 1(Win) | true |
| Jsonifier (two-stage) | 702.681 | 0.92184 | 5175.06ms | 2251027 | 80 | 6.34521e+10 | 3.05508e+06 | 1.64733 | 2(Loss) | true |
| Glaze | 644.625 | 0.965122 | 5989.83ms | 2251027 | 30 | 3.09908e+10 | 3.33023e+06 | 0.864485 | 3(Loss) | true |
| simdjson (ondemand) | 619.345 | 0.279613 | 6210.05ms | 2251027 | 30 | 2.81794e+09 | 3.46616e+06 | 0.799004 | 4(Loss) | true |
