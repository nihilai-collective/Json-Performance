
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1189.47 | 0.0873254 | 937.261ms | 11579 | 1280 | 84124.7 | 9283.59 | 0.186473 | 2.54874 | 1(Win) | true |
| Jsonifier | 1114.74 | 0.100526 | 997.692ms | 11579 | 1280 | 126930 | 9906.02 | 0.214185 | 2.71983 | 2(Loss) | true |
| simdjson (ondemand) | 747.763 | 0.11621 | 1470.32ms | 11579 | 640 | 188488 | 14767.5 | 0.0953168 | 4.05817 | 3(Loss) | true |
| Glaze | 688.567 | 0.0515454 | 1607.63ms | 11579 | 2560 | 174932 | 16037.1 | 0.0284903 | 4.40807 | 4(Loss) | true |
