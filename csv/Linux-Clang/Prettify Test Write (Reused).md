
----
### Prettify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5886.08 | 0.314793 | 5861.09ms | 699405 | 30 | 3.81748e+06 | 113319 | 0.111801 | 0.420496 | 1(Win) | true |
| Glaze | 3816.48 | 0.0974811 | 9033.82ms | 699405 | 320 | 9.28799e+06 | 174769 | 0.0949419 | 0.648614 | 2(Loss) | true |
| simdjson (ondemand) | 2539.45 | 0.212948 | 7673.12ms | 767297 | 30 | 1.12958e+07 | 288153 | 0.0434796 | 0.974812 | 3(Loss) | true |
