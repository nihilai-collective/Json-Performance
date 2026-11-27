
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 9620 | 0.0683375 | 4699.92ms | 466906 | 2560 | 2.56134e+06 | 46286.5 | 0.0218159 | 1(Win) | true |
| simdjson (stage-1) | 7648.53 | 0.126363 | 6037.42ms | 466906 | 640 | 3.46355e+06 | 58217.2 | 0.0570604 | 2(Loss) | true |
