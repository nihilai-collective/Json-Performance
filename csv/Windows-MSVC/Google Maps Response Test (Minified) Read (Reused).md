
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1547.03 | 0.0506016 | 831.399ms | 11812 | 4890 | 66387.8 | 7281.57 | 0.0189463 | 1.95955 | 1(Win) | true |
| Jsonifier (two-stage) | 1315.89 | 0.0472641 | 964.633ms | 11812 | 4890 | 80052.9 | 8560.57 | 0.0393827 | 2.30377 | 2(Loss) | true |
| Glaze | 1122.12 | 0.0933006 | 1111.61ms | 11812 | 1280 | 112291 | 10038.8 | 0.0552848 | 2.70261 | 3(Loss) | true |
| simdjson (ondemand) | 613.523 | 0.0638253 | 1955.25ms | 11812 | 1280 | 175785 | 18360.9 | 0.131306 | 4.94665 | 4(Loss) | true |
