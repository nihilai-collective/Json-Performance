
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2522.05 | 0.133524 | 2531.62ms | 53331 | 1280 | 928062 | 20166.3 | 0.0847623 | 0.980351 | 1(Win) | true |
| simdjson (reflection) | 1924.83 | 0.313883 | 3203.59ms | 53331 | 160 | 1.1006e+06 | 26423.3 | 1.0405 | 1.28486 | 2(Loss) | true |
| Jsonifier (two-stage) | 1897.62 | 0.278624 | 3062.96ms | 53331 | 2560 | 1.42764e+07 | 26802.2 | 0.131771 | 1.30335 | 3(Loss) | true |
| Glaze | 1642.84 | 0.18776 | 3535.87ms | 53331 | 2560 | 8.65e+06 | 30958.8 | 0.531811 | 1.50569 | 4(Loss) | true |
| simdjson (ondemand) | 1383.42 | 0.163528 | 4214.43ms | 53331 | 640 | 2.31321e+06 | 36764.3 | 0.383902 | 1.78832 | 5(Loss) | true |
