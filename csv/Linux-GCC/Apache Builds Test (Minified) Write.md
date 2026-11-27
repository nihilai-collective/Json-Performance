
----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20824.1 | 0.779921 | 434.663ms | 94653 | 160 | 182876 | 4334.79 | 0.302442 | 0.118146 | 1(Win) | true |
| simdjson (reflection) | 14579.7 | 0.0427903 | 645.801ms | 94653 | 40 | 280.753 | 6191.38 | 0.102532 | 0.169089 | 2(Loss) | true |
| Glaze | 5868.6 | 0.227758 | 1538.74ms | 94653 | 1280 | 1.57094e+06 | 15381.5 | 0.575961 | 0.421126 | 3(Loss) | true |
