
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2710.98 | 0.0872038 | 6387.85ms | 631514 | 1280 | 4.8039e+07 | 222155 | 0.409948 | 0.913098 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 2454.94 | 0.311306 | 6923.96ms | 631514 | 40 | 2.33302e+07 | 245325 | 0.327845 | 1.00835 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2439.83 | 0.0957309 | 7081.18ms | 631514 | 1280 | 7.14761e+07 | 246844 | 0.211007 | 1.0146 | 2(Tie) | true |
| Glaze | 2024.48 | 0.0871798 | 8284.37ms | 631514 | 320 | 2.15239e+07 | 297488 | 0.104693 | 1.22279 | 4(Loss) | true |
| simdjson (ondemand) | 1423.86 | 0.480077 | 5769.52ms | 631514 | 40 | 1.64935e+08 | 422977 | 0.721468 | 1.73865 | 5(Loss) | true |
