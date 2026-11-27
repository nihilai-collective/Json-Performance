
----
### Twitter Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4791.96 | 0.21027 | 9493.73ms | 475954 | 320 | 1.26943e+07 | 94722.2 | 0.487531 | 0.516461 | 1(Win) | true |
| Jsonifier | 3570.91 | 0.359379 | 6545.82ms | 475954 | 160 | 3.33886e+07 | 127112 | 0.168936 | 0.692863 | 2(Loss) | true |
