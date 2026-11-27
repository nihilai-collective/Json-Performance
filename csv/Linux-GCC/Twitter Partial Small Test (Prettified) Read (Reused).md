
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (reflection) | 8145.95 | 0.0487111 | 47.7383ms | 3808 | 640 | 30.1819 | 445.816 | 0.014718 | 0.286088 | 1(Win) | true |
| simdjson (ondemand) | 7783.25 | 0.0686363 | 49.4478ms | 3808 | 320 | 32.8193 | 466.591 | 0.0662615 | 0.299266 | 2(Loss) | true |
| Jsonifier (two-stage) | 7610.01 | 0.11892 | 50.4929ms | 3808 | 80 | 25.7644 | 477.212 | 0.159527 | 0.307386 | 3(Loss) | true |
| Jsonifier | 7509.01 | 0.0833235 | 51.7368ms | 3808 | 160 | 25.9827 | 483.631 | 0.00646195 | 0.311487 | 4(Loss) | true |
| Glaze | 3861.89 | 0.138651 | 101.751ms | 3808 | 30 | 50.9989 | 940.367 | 0.067395 | 0.624256 | 5(Loss) | true |
