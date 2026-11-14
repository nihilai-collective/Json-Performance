
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2242.73 | 0.396841 | 142.78ms | 2889 | 4890 | 116220 | 1228.49 | 0.512192 | 1.33464 | 1(Win) | true |
| Glaze | 1964.8 | 0.325101 | 155.842ms | 2889 | 1280 | 26601.6 | 1402.27 | 0.184193 | 1.52497 | 2(Loss) | true |
| Jsonifier (two-stage) | 1666.25 | 0.300668 | 183.73ms | 2889 | 1280 | 31637.4 | 1653.52 | 0.0519456 | 1.80443 | 3(Loss) | true |
| simdjson (ondemand) | 1514.28 | 0.133823 | 197.893ms | 2889 | 1280 | 7588.44 | 1819.45 | 0.219468 | 1.98556 | 4(Loss) | true |
