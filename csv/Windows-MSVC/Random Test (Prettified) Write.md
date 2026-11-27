
----
### Random Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3821.23 | 0.674684 | 5252.45ms | 837491 | 1280 | 2.54545e+09 | 209015 | 0.327 | 0.794659 | 1(Win) | true |
| Glaze | 2011.16 | 2.07584 | 9619.34ms | 837491 | 80 | 5.43681e+09 | 397130 | 0.259403 | 1.51003 | 2(Loss) | true |
