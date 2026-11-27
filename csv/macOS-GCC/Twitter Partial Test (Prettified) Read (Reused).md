
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 4899.22 | 0.154822 | 6503.78ms | 631514 | 160 | 5.79561e+06 | 122930 | 0.0924961 | 1(Win) | true |
| Jsonifier (two-stage) | 4743.86 | 0.297697 | 6615.12ms | 631514 | 2560 | 3.65671e+08 | 126956 | 0.79129 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 4506.63 | 0.583309 | 7436.83ms | 631514 | 80 | 4.86127e+07 | 133638 | 0.370121 | 3(Tie) | true |
| Jsonifier STATISTICAL TIE | 4466.31 | 1.69501 | 6717.59ms | 631514 | 80 | 4.17932e+08 | 134845 | 1.51041 | 3(Tie) | true |
| Glaze | 3076.87 | 0.22152 | 5227.47ms | 631514 | 640 | 1.20325e+08 | 195738 | 1.45503 | 5(Loss) | true |
