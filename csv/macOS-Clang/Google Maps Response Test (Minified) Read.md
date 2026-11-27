
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1869.03 | 0.05831 | 609.292ms | 11812 | 40 | 494.041 | 6027.1 | 0.0586585 | 1(Win) | true |
| Jsonifier (two-stage) | 1416.75 | 0.0527656 | 804.782ms | 11812 | 40 | 704.079 | 7951.15 | 0.0325006 | 2(Loss) | true |
| Glaze | 1060.85 | 0.226391 | 1066.76ms | 11812 | 640 | 369860 | 10618.7 | 0.00417914 | 3(Loss) | true |
| simdjson (ondemand) | 825.287 | 0.0623485 | 1378.92ms | 11812 | 4890 | 354159 | 13649.6 | 0.201109 | 4(Loss) | true |
