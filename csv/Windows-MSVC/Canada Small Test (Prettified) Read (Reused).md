
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1548.03 | 0.139918 | 897.112ms | 11579 | 30 | 2988.51 | 7133.33 | 0 | 1.59246 | 1(Win) | true |
| Jsonifier | 1429.9 | 0.245931 | 962.059ms | 11579 | 2560 | 923416 | 7722.62 | 0.0652082 | 1.72549 | 2(Loss) | true |
| simdjson (ondemand) | 472.79 | 0.813103 | 2581.28ms | 11579 | 80 | 2.88528e+06 | 23356.2 | 0.284457 | 5.23129 | 3(Loss) | true |
| Glaze | 424.386 | 0.250621 | 2747.84ms | 11579 | 640 | 2.72167e+06 | 26020.2 | 0.0174174 | 5.82803 | 4(Loss) | true |
