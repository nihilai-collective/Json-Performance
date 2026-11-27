
----
### Google Maps Response Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 695.49 | 0.141013 | 629.339ms | 4390 | 1280 | 92231.3 | 6019.69 | 0.147733 | 4.35455 | 1(Win) | true |
| simdjson (ondemand) | 589.874 | 0.893218 | 786.521ms | 4390 | 40 | 160763 | 7097.5 | 1.01116 | 5.13894 | 2(Loss) | true |
