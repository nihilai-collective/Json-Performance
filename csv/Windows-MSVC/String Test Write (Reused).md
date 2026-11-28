
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3625.39 | 0.327966 | 122.939ms | 4215 | 4890 | 64662.2 | 1108.77 | 0.0478973 | 0.666138 | 1(Win) | true |
| Glaze | 1865.04 | 0.500566 | 244.732ms | 4215 | 640 | 74494.4 | 2155.31 | 0.247093 | 1.3098 | 2(Loss) | true |
