
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2087.81 | 0.204571 | 616.487ms | 11812 | 2560 | 311882 | 5395.5 | 0.0870338 | 1(Win) | true |
| Jsonifier (two-stage) | 1436.7 | 0.123657 | 858.923ms | 11812 | 4890 | 459685 | 7840.72 | 0.0532851 | 2(Loss) | true |
| simdjson (reflection) | 1296.73 | 0.139489 | 946.637ms | 11812 | 2560 | 375900 | 8687.1 | 0.0587422 | 3(Loss) | true |
| Glaze | 1154.07 | 0.09788 | 1097.43ms | 11812 | 4890 | 446354 | 9760.93 | 0.131686 | 4(Loss) | true |
| simdjson (ondemand) | 816.701 | 0.0793367 | 1479.53ms | 11812 | 4890 | 585569 | 13793.1 | 0.0896915 | 5(Loss) | true |
