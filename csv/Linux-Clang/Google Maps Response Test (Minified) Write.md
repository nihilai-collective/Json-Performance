
----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12199.4 | 0.0993136 | 95.5194ms | 11812 | 80 | 67.2783 | 923.388 | 0.16623 | 0.197297 | 1(Win) | true |
| Glaze | 3135.96 | 0.199205 | 377.306ms | 11812 | 30 | 1536.12 | 3592.13 | 0.012993 | 0.783889 | 2(Loss) | true |
