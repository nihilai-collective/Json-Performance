
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3149.66 | 0.0660746 | 3590.41ms | 108313 | 4890 | 2.29621e+06 | 32795.7 | 0.0256246 | 1(Win) | true |
| Jsonifier (two-stage) | 1814.48 | 0.0592515 | 6026.22ms | 108313 | 2560 | 2.91269e+06 | 56928.2 | 0.115801 | 2(Loss) | true |
| Glaze | 1770.93 | 0.106611 | 6196.37ms | 108313 | 1280 | 4.94965e+06 | 58328.4 | 0.0541467 | 3(Loss) | true |
| simdjson (reflection) | 1431.76 | 0.168399 | 7610.43ms | 108313 | 160 | 2.36166e+06 | 72145.6 | 0.27204 | 4(Loss) | true |
| simdjson (ondemand) | 1318.84 | 0.07915 | 8278.92ms | 108313 | 2560 | 9.83827e+06 | 78322.8 | 0.0909886 | 5(Loss) | true |
