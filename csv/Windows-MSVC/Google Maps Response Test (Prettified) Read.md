
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2317.43 | 0.0861518 | 1048.6ms | 25388 | 1280 | 103701 | 10447.7 | 0.0470873 | 1.30882 | 1(Win) | true |
| Jsonifier | 2204.65 | 0.0838772 | 1104.55ms | 25388 | 1280 | 108611 | 10982.2 | 0.0227693 | 1.37595 | 2(Loss) | true |
| Glaze | 1485.9 | 0.120016 | 1635.32ms | 25388 | 640 | 244757 | 16294.4 | 0.273077 | 2.04232 | 3(Loss) | true |
| simdjson (ondemand) | 1143.28 | 0.216338 | 2144.09ms | 25388 | 160 | 335843 | 21177.5 | 0.3529 | 2.65533 | 4(Loss) | true |
