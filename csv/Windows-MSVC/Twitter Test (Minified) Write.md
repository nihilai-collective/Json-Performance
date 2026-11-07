
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 5119.46 | 0.112406 | 8981.75ms | 475954 | 2560 | 2.54274e+07 | 88662.8 | 0.182598 | 0.483375 | 1(Win) | true |
| Jsonifier | 4047.51 | 0.194925 | 5758.13ms | 475954 | 640 | 3.05821e+07 | 112144 | 0.162583 | 0.611153 | 2(Loss) | true |
