
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 12509.7 | 0.474646 | 7172.32ms | 7351818 | 640 | 4.52916e+09 | 560466 | 1.55071 | 0.242826 | 1(Win) | true |
| simdjson (stage-1) | 10509.4 | 0.582109 | 8530.05ms | 7351818 | 640 | 9.65205e+09 | 667138 | 0.959924 | 0.289074 | 2(Loss) | true |
