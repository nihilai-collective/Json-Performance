
----
### Marine IK Reverse Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6284.68 | 0.330311 | 9288.14ms | 9930848 | 160 | 3.96436e+09 | 1.50697e+06 | 0.331721 | 1(Win) | true |
| Glaze | 2862.47 | 0.445897 | 10038.6ms | 9930228 | 80 | 1.74099e+10 | 3.3084e+06 | 0.668935 | 2(Loss) | true |
| simdjson (reflection) | 302.553 | 0.82639 | 9986.72ms | 10018896 | 30 | 2.04329e+12 | 3.15805e+07 | 4.7265 | 3(Loss) | true |
