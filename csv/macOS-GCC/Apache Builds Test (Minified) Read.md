
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1159.53 | 0.0829929 | 7897.13ms | 94653 | 1280 | 5.34319e+06 | 77849.2 | 0.208686 | 1(Tie) | true |
| Glaze STATISTICAL TIE | 1153.4 | 0.312558 | 7966.64ms | 94653 | 80 | 4.78694e+06 | 78262.4 | 0.0939542 | 1(Tie) | true |
| Jsonifier (two-stage) | 1056.27 | 0.0446815 | 8943.75ms | 94653 | 4890 | 7.12995e+06 | 85459.6 | 0.367644 | 3(Loss) | true |
| simdjson (reflection) | 936.679 | 0.145847 | 5059.91ms | 94653 | 320 | 6.32168e+06 | 96370.4 | 0.227766 | 4(Loss) | true |
| simdjson (ondemand) | 767.17 | 0.0624183 | 6167.39ms | 94653 | 1280 | 6.9043e+06 | 117664 | 0.232157 | 5(Loss) | true |
