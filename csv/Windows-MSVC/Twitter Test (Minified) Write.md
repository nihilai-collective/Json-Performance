
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 4581.36 | 0.849508 | 5028.3ms | 475954 | 2560 | 1.8135e+09 | 99076.5 | 0.0972103 | 0.663074 | 1(Win) | true |
| Jsonifier | 3721.01 | 1.02768 | 6392.43ms | 475954 | 640 | 1.00578e+09 | 121985 | 0.66002 | 0.815785 | 2(Loss) | true |
